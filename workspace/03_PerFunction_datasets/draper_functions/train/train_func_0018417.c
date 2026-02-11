qla82xx_md_prep(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	int rval;


	rval = qla82xx_md_get_template_size(vha);
	if (rval == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0xb04a,
		    "MiniDump Template size obtained (%d KB)\n",
		    ha->md_template_size / 1024);


		if (IS_QLA8044(ha))
			rval = qla8044_md_get_template(vha);
		else
			rval = qla82xx_md_get_template(vha);

		if (rval == QLA_SUCCESS) {
			ql_dbg(ql_dbg_p3p, vha, 0xb04b,
			    "MiniDump Template obtained\n");


			rval = qla82xx_md_alloc(vha);
			if (rval == QLA_SUCCESS)
				ql_log(ql_log_info, vha, 0xb04c,
				    "MiniDump memory allocated (%d KB)\n",
				    ha->md_dump_size / 1024);
			else {
				ql_log(ql_log_info, vha, 0xb04d,
				    "Free MiniDump template: %p, size: (%d KB)\n",
				    ha->md_tmplt_hdr,
				    ha->md_template_size / 1024);
				dma_free_coherent(&ha->pdev->dev,
				    ha->md_template_size,
				    ha->md_tmplt_hdr, ha->md_tmplt_hdr_dma);
				ha->md_tmplt_hdr = NULL;
			}

		}
	}
}
