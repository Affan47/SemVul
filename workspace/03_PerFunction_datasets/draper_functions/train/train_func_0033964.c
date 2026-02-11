nand_setup_cmd_params(struct platform_device *pdev,
				 struct goldfish_nand *nand)
{
	u64 paddr;
	unsigned char __iomem  *base = nand->base;

	nand->cmd_params = devm_kzalloc(&pdev->dev,
					sizeof(struct cmd_params), GFP_KERNEL);
	if (!nand->cmd_params)
		return -1;

	paddr = __pa(nand->cmd_params);
	writel((u32)(paddr >> 32), base + NAND_CMD_PARAMS_ADDR_HIGH);
	writel((u32)paddr, base + NAND_CMD_PARAMS_ADDR_LOW);
	return 0;
}
