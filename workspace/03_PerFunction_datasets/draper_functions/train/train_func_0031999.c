load_session_vars(const char *target, std::map<std::string, std::string> &varmap)
{
	PHP_EXP_NODE *sess_vars_exp_node = get_var_node(target);
	PHP_VAR_NODE *sess_vars = sess_vars_exp_node->var_si_node->var;

	delete sess_vars_exp_node;
	cast_value_array(&sess_vars->value);


#if 0
	for(std::map<std::string, std::string>::iterator i = varmap.begin(); i != varmap.end(); i++) {
#else
	for(std::map<std::string, std::string>::iterator i = varmap.begin(); i != varmap.end(); ++i) {
#endif

		PHP_VAR_NODE *curr_var = array_get_by_str_key(&sess_vars->value, i->first);
		PHP_VALUE_NODE val;
		val.type = PHP_VAL_STRING;
		val.str_val = const_cast<char *>(i->second.c_str());
		value_value_assign(&curr_var->value, &val);
	}
}
