CreateConfigTest(const char* config)
{
  std::string result = "\"${CMAKE_INSTALL_CONFIG_NAME}\" MATCHES \"^(";
  if(config && *config)
    {
    cmInstallGeneratorEncodeConfig(config, result);
    }
  result += ")$\"";
  return result;
}
