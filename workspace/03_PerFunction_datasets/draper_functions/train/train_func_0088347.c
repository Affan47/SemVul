draw_rich_preview (glMiniPreview          *this,
                   cairo_t                *cr)
{
        glMerge      *merge;
        glPrintState  state;

        merge = gl_label_get_merge (this->priv->label);

        if (!merge)
        {
                gl_print_simple_sheet (this->priv->label,
                                       cr,
                                       this->priv->page,
                                       this->priv->n_sheets,
                                       this->priv->first,
                                       this->priv->last,
                                       this->priv->outline_flag,
                                       this->priv->reverse_flag,
                                       this->priv->crop_marks_flag);
        }
        else
        {


                state.i_copy = 0;
                state.p_record = (GList *)gl_merge_get_record_list (merge);

                if (this->priv->collate_flag)
                {
                        gl_print_collated_merge_sheet (this->priv->label,
                                                       cr,
                                                       this->priv->page,
                                                       this->priv->n_copies,
                                                       this->priv->first,
                                                       this->priv->outline_flag,
                                                       this->priv->reverse_flag,
                                                       this->priv->crop_marks_flag,
                                                       &state);
                }
                else
                {
                        gl_print_uncollated_merge_sheet (this->priv->label,
                                                         cr,
                                                         this->priv->page,
                                                         this->priv->n_copies,
                                                         this->priv->first,
                                                         this->priv->outline_flag,
                                                         this->priv->reverse_flag,
                                                         this->priv->crop_marks_flag,
                                                         &state);
                }
        }
}
