fwe_probe(struct fmc_device *fmc)
{
	int err, index = 0;
	const struct firmware *fw;
	struct device *dev = &fmc->dev;
	char *s;

	if (!fwe_drv.busid_n) {
		dev_err(dev, "%s: no busid passed, refusing all cards\n",
			KBUILD_MODNAME);
		return -ENODEV;
	}
	if (fmc->op->validate)
		index = fmc->op->validate(fmc, &fwe_drv);
	if (index < 0) {
		pr_err("%s: refusing device \"%s\"\n", KBUILD_MODNAME,
		       dev_name(dev));
		return -ENODEV;
	}
	if (index >= fwe_file_n) {
		pr_err("%s: no filename for device index %i\n",
			KBUILD_MODNAME, index);
		return -ENODEV;
	}
	s = fwe_file[index];
	if (!s) {
		pr_err("%s: no filename for \"%s\" not programming\n",
		       KBUILD_MODNAME, dev_name(dev));
		return -ENOENT;
	}
	err = request_firmware(&fw, s, dev);
	if (err < 0) {
		dev_err(&fmc->dev, "request firmware \"%s\": error %i\n",
			s, err);
		return err;
	}
	fwe_run(fmc, fw, s);
	release_firmware(fw);
	return 0;
}
