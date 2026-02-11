mx27_camera_emma_init(struct platform_device *pdev)
{
	struct mx2_camera_dev *pcdev = platform_get_drvdata(pdev);
	struct resource *res_emma;
	int irq_emma;
	int err = 0;

	res_emma = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	irq_emma = platform_get_irq(pdev, 1);
	if (!res_emma || !irq_emma) {
		dev_err(pcdev->dev, "no EMMA resources\n");
		err = -ENODEV;
		goto out;
	}

	pcdev->base_emma = devm_ioremap_resource(pcdev->dev, res_emma);
	if (IS_ERR(pcdev->base_emma)) {
		err = PTR_ERR(pcdev->base_emma);
		goto out;
	}

	err = devm_request_irq(pcdev->dev, irq_emma, mx27_camera_emma_irq, 0,
			       MX2_CAM_DRV_NAME, pcdev);
	if (err) {
		dev_err(pcdev->dev, "Camera EMMA interrupt register failed\n");
		goto out;
	}

	pcdev->clk_emma_ipg = devm_clk_get(pcdev->dev, "emma-ipg");
	if (IS_ERR(pcdev->clk_emma_ipg)) {
		err = PTR_ERR(pcdev->clk_emma_ipg);
		goto out;
	}

	clk_prepare_enable(pcdev->clk_emma_ipg);

	pcdev->clk_emma_ahb = devm_clk_get(pcdev->dev, "emma-ahb");
	if (IS_ERR(pcdev->clk_emma_ahb)) {
		err = PTR_ERR(pcdev->clk_emma_ahb);
		goto exit_clk_emma_ipg;
	}

	clk_prepare_enable(pcdev->clk_emma_ahb);

	err = mx27_camera_emma_prp_reset(pcdev);
	if (err)
		goto exit_clk_emma_ahb;

	return err;

exit_clk_emma_ahb:
	clk_disable_unprepare(pcdev->clk_emma_ahb);
exit_clk_emma_ipg:
	clk_disable_unprepare(pcdev->clk_emma_ipg);
out:
	return err;
}
