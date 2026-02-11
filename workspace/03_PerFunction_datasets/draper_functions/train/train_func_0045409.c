qla2x00_free_fw_dump(struct qla_hw_data *ha)
{
	if (ha->fce)
		dma_free_coherent(&ha->pdev->dev,
		    FCE_SIZE, ha->fce, ha->fce_dma);

	if (ha->eft)
		dma_free_coherent(&ha->pdev->dev,
		    EFT_SIZE, ha->eft, ha->eft_dma);

	if (ha->fw_dump)
		vfree(ha->fw_dump);
	if (ha->fw_dump_template)
		vfree(ha->fw_dump_template);

	ha->fce = NULL;
	ha->fce_dma = 0;
	ha->eft = NULL;
	ha->eft_dma = 0;
	ha->fw_dumped = 0;
	ha->fw_dump_cap_flags = 0;
	ha->fw_dump_reading = 0;
	ha->fw_dump = NULL;
	ha->fw_dump_len = 0;
	ha->fw_dump_template = NULL;
	ha->fw_dump_template_len = 0;
}
