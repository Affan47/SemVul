setDialRules(const char* name)
{
    delete dialRules;
    dialRules = new MyDialStringRules(name);
    dialRules->setVerbose((tracingLevel & FAXTRACE_DIALRULES) != 0);


    dialRules->def("AreaCode", areaCode);
    dialRules->def("CountryCode", countryCode);
    dialRules->def("LongDistancePrefix", longDistancePrefix);
    dialRules->def("InternationalPrefix", internationalPrefix);
    if (!dialRules->parse()) {
	configError("Parse error in dial string rules \"%s\"", name);
	delete dialRules, dialRules = NULL;
    }
}
