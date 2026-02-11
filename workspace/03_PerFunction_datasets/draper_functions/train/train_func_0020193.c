merge_ea(const ea_attributs & ref1, const ea_attributs & ref2, ea_attributs &res)
    {
	string ent_key, ent_val;
	string val;

	res = ref1;
	res.reset_read();

	ref2.reset_read();
	while(ref2.read(ent_key, ent_val))
	    if(!res.find(ent_key, val))
		res.add(ent_key, ent_val);
    }
