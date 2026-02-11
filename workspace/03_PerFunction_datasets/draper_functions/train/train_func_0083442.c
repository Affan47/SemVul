BuildPackage(void)
{
	QString packagePath = PromptFileCreation("Save Package", "*.tar.gz");

	if (!packagePath.isEmpty())
	{
		if (!packagePath.endsWith(".tar.gz", Qt::CaseInsensitive))
		{
			if (packagePath.endsWith(".tar", Qt::CaseInsensitive))
				packagePath.append(".gz");
			else if (packagePath.endsWith(".gz", Qt::CaseInsensitive))
				packagePath.replace(packagePath.length() - 3, ".tar.gz");
			else if (packagePath.endsWith(".tgz", Qt::CaseInsensitive))
				packagePath.replace(packagePath.length() - 4, ".tar.gz");
			else
				packagePath.append(".tar.gz");
		}

		Packaging::BuildPackage(packagePath, workingPackageData.GetFirmwareInfo());
	}
}
