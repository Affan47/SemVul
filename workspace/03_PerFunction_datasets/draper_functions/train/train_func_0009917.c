C4_Model_insert_calcs(C4_Model *target, C4_Model *insert,
                                  C4_Calc **calc_map){
    register gint i;
    register C4_Calc *insert_calc, *target_calc;
    for(i = 0; i < insert->calc_list->len; i++){
        insert_calc = insert->calc_list->pdata[i];
        target_calc = C4_Model_match_calc(target, insert_calc);
        if(!target_calc)
            target_calc = C4_Model_add_calc(target, insert_calc->name,
                insert_calc->max_score,
                insert_calc->calc_func, insert_calc->calc_macro,
                insert_calc->init_func, insert_calc->init_macro,
                insert_calc->exit_func, insert_calc->exit_macro,
                insert_calc->protect);
        calc_map[insert_calc->id] = target_calc;
        }
    return;
    }
