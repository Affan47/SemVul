qed_hw_prepare(struct qed_dev *cdev,
		   int personality)
{
	struct qed_hwfn *p_hwfn = QED_LEADING_HWFN(cdev);
	int rc;


	qed_init_iro_array(cdev);


	rc = qed_hw_prepare_single(p_hwfn,
				   cdev->regview,
				   cdev->doorbells, personality);
	if (rc)
		return rc;

	personality = p_hwfn->hw_info.personality;


	if (cdev->num_hwfns > 1) {
		void __iomem *p_regview, *p_doorbell;
		u8 __iomem *addr;


		addr = cdev->regview + qed_hw_bar_size(p_hwfn, 0) / 2;
		p_regview = addr;


		addr = cdev->doorbells + qed_hw_bar_size(p_hwfn, 1) / 2;
		p_doorbell = addr;


		rc = qed_hw_prepare_single(&cdev->hwfns[1], p_regview,
					   p_doorbell, personality);


		if (rc) {
			qed_init_free(p_hwfn);
			qed_mcp_free(p_hwfn);
			qed_hw_hwfn_free(p_hwfn);
		}
	}

	return rc;
}
