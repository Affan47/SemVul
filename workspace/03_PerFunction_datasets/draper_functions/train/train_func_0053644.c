gnc_tree_model_split_reg_get_row_color (GncTreeModelSplitReg *model, gboolean is_trow1, gboolean is_trow2, gboolean is_split, gint num)
{

    gchar *cell_color = NULL;

    if (!model->use_theme_colors)
    {
        if (model->use_double_line)
        {
            if (model->alt_colors_by_txn)
            {
                if (num % 2 == 0)
                {
                    if (is_trow1 || is_trow2)
                        cell_color = (gchar*)GREENROW;
                }
                else
                {
                    if (is_trow1 || is_trow2)
                        cell_color = (gchar*)TANROW;
                }
            }
            else
            {
                if (is_trow1)
                    cell_color = (gchar*)GREENROW;
                else if (is_trow2)
                    cell_color = (gchar*)TANROW;
            }
        }
        else
        {
            if (num % 2 == 0)
            {
                if (is_trow1)
                    cell_color = (gchar*)GREENROW;
                else if (is_trow2)
                    cell_color = (gchar*)TANROW;
            }
            else
            {
                if (is_trow1)
                    cell_color = (gchar*)TANROW;
                else if (is_trow2)
                    cell_color = (gchar*)GREENROW;
            }
        }
        if (is_split)
            cell_color = (gchar*)SPLITROW;
    }
    else
        cell_color = (gchar*)NULL;

    return cell_color;
}
