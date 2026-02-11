gnc_tree_util_split_reg_get_value_for (GncTreeViewSplitReg *view, Transaction *trans, Split *split, gboolean is_blank)
{
    gnc_numeric        ret_num;
    GNCPrintAmountInfo ret_print_info;

    if (gnc_tree_util_split_reg_get_debcred_entry (view, trans, split, is_blank, &ret_num, &ret_print_info))
        return ret_num;
    else
        return gnc_numeric_zero();
}
