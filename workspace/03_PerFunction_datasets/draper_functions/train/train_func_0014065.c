FixModuleRfmVar(void)
{
    RfmVar var;
    RfmVar next;
    RfmVar var_tail = NULL;
    RfmVar return_var = NULL;
    RfmVar generate_var_head = NULL;
    RfmVar generate_var_tail = NULL;

    var = RFM_ModuleCurrent->var_list;
    while (var) {
        next = var->next;
        if (var->is_rtn_var) {
            if (var->prev) {
                var->prev->next = var->next;
            } else {
                RFM_ModuleCurrent->var_list = var->next;
            }
            if (var->next) {
                var->next->prev = var->prev;
            }
            var->prev = NULL;
            var->next = NULL;
            return_var = var;
        } else if (var->is_generate) {
            if (var->prev) {
                var->prev->next = var->next;
            } else {
                RFM_ModuleCurrent->var_list = var->next;
            }
            if (var->next) {
                var->next->prev = var->prev;
            }
            if (generate_var_tail) {
                generate_var_tail->next = var;
                var->prev = generate_var_tail;
                generate_var_tail = var;
            } else {
                generate_var_head = var;
                generate_var_tail = var;
            }
        } else {
            var_tail = var;
        }
        var = next;
    }
    if (generate_var_head) {
        if (var_tail) {
            var_tail->next = generate_var_head;
            generate_var_head->prev = var_tail;
            var_tail = generate_var_tail;
        } else {
            RFM_ModuleCurrent->var_list = generate_var_head;
            var_tail = generate_var_tail;
        }
    }
    if (return_var) {
        if (var_tail) {
            var_tail->next = return_var;
            return_var->prev = var_tail;
        } else {
            RFM_ModuleCurrent->var_list = return_var;
        }
    }

    for (var = RFM_ModuleCurrent->var_list;
         var != NULL;
         var = var->next) {
        var->entry = (var->prev)?(var->prev->entry + 1):
                                 RFM_Global->var_num + 1;
        var->is_global = FALSE;
        var->module = RFM_ModuleCurrent;
    }
}
