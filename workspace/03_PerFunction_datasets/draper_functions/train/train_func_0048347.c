power_down_vsb(struct drx_demod_instance *demod, bool primary)
{
	struct i2c_device_addr *dev_addr = demod->my_i2c_dev_addr;
	struct drxjscu_cmd cmd_scu = {  0,
		 0,
		 0,
		 NULL,
		 NULL
	};
	struct drx_cfg_mpeg_output cfg_mpeg_output;
	int rc;
	u16 cmd_result = 0;


	cmd_scu.command = SCU_RAM_COMMAND_STANDARD_VSB |
	    SCU_RAM_COMMAND_CMD_DEMOD_STOP;
	cmd_scu.parameter_len = 0;
	cmd_scu.result_len = 1;
	cmd_scu.parameter = NULL;
	cmd_scu.result = &cmd_result;
	rc = scu_command(dev_addr, &cmd_scu);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}


	rc = drxj_dap_write_reg16(dev_addr, FEC_COMM_EXEC__A, FEC_COMM_EXEC_STOP, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	rc = drxj_dap_write_reg16(dev_addr, VSB_COMM_EXEC__A, VSB_COMM_EXEC_STOP, 0);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}
	if (primary) {
		rc = drxj_dap_write_reg16(dev_addr, IQM_COMM_EXEC__A, IQM_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = set_iqm_af(demod, false);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	} else {
		rc = drxj_dap_write_reg16(dev_addr, IQM_FS_COMM_EXEC__A, IQM_FS_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_FD_COMM_EXEC__A, IQM_FD_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_RC_COMM_EXEC__A, IQM_RC_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_RT_COMM_EXEC__A, IQM_RT_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
		rc = drxj_dap_write_reg16(dev_addr, IQM_CF_COMM_EXEC__A, IQM_CF_COMM_EXEC_STOP, 0);
		if (rc != 0) {
			pr_err("error %d\n", rc);
			goto rw_error;
		}
	}

	cfg_mpeg_output.enable_mpeg_output = false;
	rc = ctrl_set_cfg_mpeg_output(demod, &cfg_mpeg_output);
	if (rc != 0) {
		pr_err("error %d\n", rc);
		goto rw_error;
	}

	return 0;
rw_error:
	return rc;
}
