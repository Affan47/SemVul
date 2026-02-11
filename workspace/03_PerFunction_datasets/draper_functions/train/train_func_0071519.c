ath_desc_alloc(struct ath_softc_tgt *sc)
{
#define DS2PHYS(_dd, _ds)						\
	((_dd)->dd_desc_paddr + ((caddr_t)(_ds) - (caddr_t)(_dd)->dd_desc))

	a_int32_t error;
	struct ath_tx_buf *bf;

	if(ath_numrxbufs == -1)
		ath_numrxbufs = ATH_RXBUF;

	if (ath_numrxdescs == -1)
		ath_numrxdescs = ATH_RXDESC;

	error = ath_descdma_setup(sc, &sc->sc_rxdma, (ath_bufhead *)&sc->sc_rxbuf,
				  "rx", ath_numrxdescs, 1,
				  sizeof(struct ath_rx_buf),
				  sizeof(struct ath_rx_desc));
	if (error != 0)
		return error;

	a_uint32_t i;
	struct ath_descdma *dd = &sc->sc_rxdma;
	struct ath_rx_desc *ds = (struct ath_rx_desc *)dd->dd_desc;
	struct ath_rx_desc *ds_prev = NULL;

	asf_tailq_init(&sc->sc_rxdesc);
	asf_tailq_init(&sc->sc_rxdesc_idle);

	for (i = 0; i < ath_numrxdescs; i++, ds++) {

		if (ds->ds_nbuf != ADF_NBUF_NULL) {
			ds->ds_nbuf = ADF_NBUF_NULL;
		}

		if (adf_nbuf_dmamap_create(sc->sc_dev, &ds->ds_dmap) != A_STATUS_OK) {
			adf_os_assert(0);
		}

		ds->ds_daddr = DS2PHYS(&sc->sc_rxdma, ds);

		if (ds_prev) {
			ds_prev->ds_link = ds->ds_daddr;
		}

		ds->ds_link = 0;
		ds_prev = ds;

		asf_tailq_insert_tail(&sc->sc_rxdesc, ds, ds_list);
	}

	error = ath_descdma_setup(sc, &sc->sc_txdma, (ath_bufhead *)&sc->sc_txbuf,
				  "tx", ATH_TXBUF + 1, ATH_TXDESC,
				  sizeof(struct ath_tx_buf),
				  sizeof(struct ath_tx_desc));
	if (error != 0) {
		ath_descdma_cleanup(sc, &sc->sc_rxdma, (ath_bufhead *)&sc->sc_rxbuf,
				    ADF_OS_DMA_FROM_DEVICE);
		return error;
	}

	error = ath_descdma_setup(sc, &sc->sc_bdma, (ath_bufhead *)&sc->sc_bbuf,
				  "beacon", ATH_BCBUF, 1,
				  sizeof(struct ath_tx_buf),
				  sizeof(struct ath_tx_desc));
	if (error != 0) {
		ath_descdma_cleanup(sc, &sc->sc_txdma, (ath_bufhead *)&sc->sc_txbuf,
				    ADF_OS_DMA_TO_DEVICE);
		ath_descdma_cleanup(sc, &sc->sc_rxdma, (ath_bufhead *)&sc->sc_rxbuf,
				    ADF_OS_DMA_FROM_DEVICE);
		return error;
	}

	bf = asf_tailq_first(&sc->sc_txbuf);
	bf->bf_isaggr = bf->bf_isretried = bf->bf_retries = 0;
	asf_tailq_remove(&sc->sc_txbuf, bf, bf_list);

	sc->sc_txbuf_held = bf;

	return 0;

#undef DS2PHYS
}
