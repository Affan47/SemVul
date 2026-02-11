cz_ih_get_wptr(struct amdgpu_device *adev)
{
	u32 wptr, tmp;

	wptr = le32_to_cpu(adev->wb.wb[adev->irq.ih.wptr_offs]);

	if (REG_GET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW)) {
		wptr = REG_SET_FIELD(wptr, IH_RB_WPTR, RB_OVERFLOW, 0);


		dev_warn(adev->dev, "IH ring buffer overflow (0x%08X, 0x%08X, 0x%08X)\n",
			wptr, adev->irq.ih.rptr, (wptr + 16) & adev->irq.ih.ptr_mask);
		adev->irq.ih.rptr = (wptr + 16) & adev->irq.ih.ptr_mask;
		tmp = RREG32(mmIH_RB_CNTL);
		tmp = REG_SET_FIELD(tmp, IH_RB_CNTL, WPTR_OVERFLOW_CLEAR, 1);
		WREG32(mmIH_RB_CNTL, tmp);
	}
	return (wptr & adev->irq.ih.ptr_mask);
}
