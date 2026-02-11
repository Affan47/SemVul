totalXSecExp() const {
  if(totalXSecExp_ != 0*millibarn)
    return totalXSecExp_;

  double pom_old = 0.0808;
  CrossSection coef_old = 21.7*millibarn;
  double pom_new_hard = 0.452;
  CrossSection coef_new_hard = 0.0139*millibarn;
  double pom_new_soft = 0.0667;
  CrossSection coef_new_soft = 24.22*millibarn;

  Energy energy(generator()->maximumCMEnergy());

  switch(DLmode_){
  case 1:
    return coef_old * pow(energy/GeV, 2*pom_old);
    break;

  case 2:
    return 81.8*millibarn * pow(energy/1800.0/GeV, 2*pom_old);
    break;

  case 3:
    return coef_new_hard * pow(energy/GeV, 2*pom_new_hard) +
      coef_new_soft * pow(energy/GeV, 2*pom_new_soft);
    break;

  default:
    throw Exception() << "MPIHandler::totalXSecExp non-existing mode selected"
                      << Exception::runerror;
  }
}
