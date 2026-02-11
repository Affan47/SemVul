func_scope_init(PHP_FUNC_PARAM_DEF *params, int param_count,
	PHP_SCOPE_TABLE_TYPE * , PHP_VALUE_NODE *arg_array,
	std::map<std::string, PHP_VAR_NODE *> &saved_vars)
{


	PHP_SCOPE_TABLE_TYPE *curr_scope_map = (PHP_SCOPE_TABLE_TYPE *)g_current_scope;
	for(PHP_SCOPE_TABLE_TYPE::iterator i = curr_scope_map->begin(); i != curr_scope_map->end();i++) {
		if ( (i->second->type == PHP_SCOPE_VAR) || (i->second->type == PHP_SCOPE_PARAM) ) {
			if ( !(i->second->var->flags & PHP_VARFLAG_STATIC) ) {

				saved_vars[i->first] = i->second->var;
			}
		}
	}


	PHP_VAR_NODE *call_params[PHP_MAX_FUNC_PARAM];
	for(int i = 0; i < param_count; i++) {
		PHP_VAR_NODE *curr_arg_val = array_get_by_int_key(arg_array, i);
		if ( curr_arg_val->value.type != PHP_VAL_NONE ) {
			if ( (curr_arg_val->flags & PHP_VARFLAG_BYREF) || params[i].byref ) {
				call_params[i] = php_expr_eval_lvalue((PHP_EXP_NODE *)curr_arg_val->value.ptr_val);
				if ( !call_params[i] ) {
					php_report_error(PHP_ERROR, "Byref parameter is not lvalue");
					return;
				}
			} else {
				call_params[i] = make_var_node();
				call_params[i]->ref_count = 1;

				php_expr_eval((PHP_EXP_NODE *)curr_arg_val->value.ptr_val, &call_params[i]->value);
			}
		} else {

			php_report_error(PHP_WARNING, "Default parameters are not implemented yet");
			call_params[i] = make_var_node();
			call_params[i]->ref_count = 1;
		}
	}


	for(int i = 0; i < param_count; i++) {

		params[i].si_var->var = call_params[i];
	}


	for(PHP_SCOPE_TABLE_TYPE::iterator i = curr_scope_map->begin(); i != curr_scope_map->end();i++) {
		if ( !((i->second->type == PHP_SCOPE_PARAM) || (i->second->type == PHP_SCOPE_VAR)) ) {
			continue;
		}


		if ( !(i->second->var->flags & PHP_VARFLAG_STATIC) && (i->second->type != PHP_SCOPE_PARAM) ) {

			i->second->var = make_var_node();
			i->second->var->ref_count = 1;
		}
	}
}
