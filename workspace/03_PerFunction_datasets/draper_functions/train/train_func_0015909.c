ipmi_chassis_print_power_status(struct ipmi_intf * intf)
{
   int ps = ipmi_chassis_power_status(intf);

   if (ps < 0)
      return -1;

   printf("Chassis Power is %s\n", ps ? "on" : "off");

   return 0;
}
