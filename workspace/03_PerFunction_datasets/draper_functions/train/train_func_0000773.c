get_adc_configmask(unsigned int reg)
{

    if (mValidCfgBits <= 0xf)
    {
      return (m_configuration_bits[(reg >>  mCfgBitShift) & mValidCfgBits]);
    }
    else
    {
      return (~(reg >> mCfgBitShift) & mValidCfgBits);
    }
}
