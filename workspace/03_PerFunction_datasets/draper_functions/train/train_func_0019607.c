gnc_tree_model_split_reg_config (GncTreeModelSplitReg *model, SplitRegisterType2 newtype,
                                 SplitRegisterStyle2 newstyle, gboolean use_double_line)
{
    model->type = newtype;

    if (model->type >= NUM_SINGLE_REGISTER_TYPES2)
        newstyle = REG2_STYLE_JOURNAL;

    model->style = newstyle;
    model->use_double_line = use_double_line;
}
