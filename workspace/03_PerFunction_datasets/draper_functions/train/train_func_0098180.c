addPairIG(const CRotFrictionIGP &prms)
{
  RotIGPCommand igpCmd(getGlobalRankAndComm());
  igpCmd.appendIGP(prms);
  igpCmd.append(prms.k);
  igpCmd.append(prms.mu_s);
  igpCmd.append(prms.mu_d);
  igpCmd.append(prms.k_s);
  igpCmd.append(prms.dt);
  igpCmd.append(static_cast<int>(prms.scaling));
  igpCmd.append(static_cast<int>(prms.meanR_scaling));
  igpCmd.broadcast();
}
