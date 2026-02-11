evaluateFromFileOptions(OFCommandLine& cmd,
                                           Image2Dcm& converter)
{
  OFCondition cond;

  if ( cmd.findOption("--dataset-from") )
  {
    OFString tempStr;
    OFCommandLine::E_ValueStatus valStatus;
    valStatus = cmd.getValue(tempStr);
    if (valStatus != OFCommandLine::VS_Normal)
      return makeOFCondition(OFM_dcmdata, 18, OF_error, "Unable to read value of --dataset-from option");
    converter.setTemplateFile(tempStr);
  }

  if (cmd.findOption("--study-from"))
  {
    OFString tempStr;
    OFCommandLine::E_ValueStatus valStatus;
    valStatus = cmd.getValue(tempStr);
    if (valStatus != OFCommandLine::VS_Normal)
      return makeOFCondition(OFM_dcmdata, 18, OF_error, "Unable to read value of --study-from option");
    converter.setStudyFrom(tempStr);
  }

  if (cmd.findOption("--series-from"))
  {
    OFString tempStr;
    OFCommandLine::E_ValueStatus valStatus;
    valStatus = cmd.getValue(tempStr);
    if (valStatus != OFCommandLine::VS_Normal)
      return makeOFCondition(OFM_dcmdata, 18, OF_error, "Unable to read value of --series-from option");
    converter.setSeriesFrom(tempStr);
  }

  if (cmd.findOption("--instance-inc"))
    converter.setIncrementInstanceNumber(OFTrue);


  return EC_Normal;
}
