qla2x00_get_thermal_temp(scsi_qla_host_t *vha, uint16_t *temp)
{
	int rval = QLA_FUNCTION_FAILED;
	struct qla_hw_data *ha = vha->hw;
	uint8_t byte;

	if (!IS_FWI2_CAPABLE(ha) || IS_QLA24XX_TYPE(ha) || IS_QLA81XX(ha)) {
		ql_dbg(ql_dbg_mbx, vha, 0x1150,
		    "Thermal not supported by this card.\n");
		return rval;
	}

	if (IS_QLA25XX(ha)) {
		if (ha->pdev->subsystem_vendor == PCI_VENDOR_ID_QLOGIC &&
		    ha->pdev->subsystem_device == 0x0175) {
			rval = qla2x00_read_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_13|BIT_0);
			*temp = byte;
			return rval;
		}
		if (ha->pdev->subsystem_vendor == PCI_VENDOR_ID_HP &&
		    ha->pdev->subsystem_device == 0x338e) {
			rval = qla2x00_read_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_15|BIT_14|BIT_0);
			*temp = byte;
			return rval;
		}
		ql_dbg(ql_dbg_mbx, vha, 0x10c9,
		    "Thermal not supported by this card.\n");
		return rval;
	}

	if (IS_QLA82XX(ha)) {
		*temp = qla82xx_read_temperature(vha);
		rval = QLA_SUCCESS;
		return rval;
	} else if (IS_QLA8044(ha)) {
		*temp = qla8044_read_temperature(vha);
		rval = QLA_SUCCESS;
		return rval;
	}

	rval = qla2x00_read_asic_temperature(vha, temp);
	return rval;
}
