set_module_and_type(char const* package_name, char const* type_attribute_name)
{
    state = unknown;
    module_name = package_name ? package_name : "" ;
    type_name = type_attribute_name ? type_attribute_name : "" ;
}
