ath_pci_remove(struct pci_device *pdev)
{
	struct net80211_device *dev = pci_get_drvdata(pdev);
	struct ath_softc *sc = dev->priv;
	void *mem = sc->mem;

	if (!is_ath9k_unloaded)
		sc->sc_ah->ah_flags |= AH_UNPLUGGED;
	ath9k_deinit_device(sc);
	net80211_free(sc->dev);

	iounmap(mem);
}
