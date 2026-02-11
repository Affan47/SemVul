add_anon_element(ElementClassT *type, const String &config,
			  const LandmarkT &landmark)
{
    String name = ";" + type->name() + "@" + String(_n_live_elements + 1);
    ElementT *result = add_element(ElementT(name, type, config, landmark));
    assign_element_name(result->eindex());
    return result;
}
