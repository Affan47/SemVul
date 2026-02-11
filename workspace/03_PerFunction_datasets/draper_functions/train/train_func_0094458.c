PCIDSK2GetInterfaces()
{
    static VSI_IOInterface singleton_vsi_interface;
    static PCIDSKInterfaces singleton_pcidsk2_interfaces;

    singleton_pcidsk2_interfaces.io = &singleton_vsi_interface;
    singleton_pcidsk2_interfaces.OpenEDB = GDAL_EDBOpen;

    return &singleton_pcidsk2_interfaces;
}
