dwc3_pci_quirks(struct pci_dev *pdev)
{
	if (pdev->vendor == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_NL_USB) {
		struct dwc3_platform_data pdata;

		memset(&pdata, 0, sizeof(pdata));

		pdata.has_lpm_erratum = true;
		pdata.lpm_nyet_threshold = 0xf;

		pdata.u2exit_lfps_quirk = true;
		pdata.u2ss_inp3_quirk = true;
		pdata.req_p1p2p3_quirk = true;
		pdata.del_p1p2p3_quirk = true;
		pdata.del_phy_power_chg_quirk = true;
		pdata.lfps_filter_quirk = true;
		pdata.rx_detect_poll_quirk = true;

		pdata.tx_de_emphasis_quirk = true;
		pdata.tx_de_emphasis = 1;


		pdata.disable_scramble_quirk = true;
		pdata.dis_u3_susphy_quirk = true;
		pdata.dis_u2_susphy_quirk = true;

		return platform_device_add_data(pci_get_drvdata(pdev), &pdata,
						sizeof(pdata));
	}

	if (pdev->vendor == PCI_VENDOR_ID_INTEL &&
	    pdev->device == PCI_DEVICE_ID_INTEL_BYT) {
		struct gpio_desc *gpio;

		acpi_dev_add_driver_gpios(ACPI_COMPANION(&pdev->dev),
					  acpi_dwc3_byt_gpios);


		gpio = gpiod_get_optional(&pdev->dev, "cs", GPIOD_OUT_LOW);
		if (IS_ERR(gpio))
			return PTR_ERR(gpio);

		gpiod_set_value_cansleep(gpio, 1);
		gpiod_put(gpio);

		gpio = gpiod_get_optional(&pdev->dev, "reset", GPIOD_OUT_LOW);
		if (IS_ERR(gpio))
			return PTR_ERR(gpio);

		if (gpio) {
			gpiod_set_value_cansleep(gpio, 1);
			gpiod_put(gpio);
			usleep_range(10000, 11000);
		}
	}

	if (pdev->vendor == PCI_VENDOR_ID_SYNOPSYS &&
	    (pdev->device == PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3 ||
	     pdev->device == PCI_DEVICE_ID_SYNOPSYS_HAPSUSB3_AXI ||
	     pdev->device == PCI_DEVICE_ID_SYNOPSYS_HAPSUSB31)) {

		struct dwc3_platform_data pdata;

		memset(&pdata, 0, sizeof(pdata));
		pdata.usb3_lpm_capable = true;
		pdata.has_lpm_erratum = true;
		pdata.dis_enblslpm_quirk = true;

		return platform_device_add_data(pci_get_drvdata(pdev), &pdata,
						sizeof(pdata));
	}

	return 0;
}
