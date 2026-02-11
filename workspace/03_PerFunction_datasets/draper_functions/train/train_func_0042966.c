t1_hinter__init(t1_hinter * self, gx_path *output_path)
{   self->max_import_coord = (1 << max_coord_bits);
    self->stem_snap_count[0] = self->stem_snap_count[1] = 0;
    self->stem_snap_vote_count = 0;
    self->zone_count = 0;
    self->pole_count = 0;
    self->hint_count = 0;
    self->contour_count = 0;
    self->subglyph_count = 0;
    self->hint_range_count = 0;
    self->flex_count = 0;
    self->have_flex = false;

    self->max_subglyph_count = count_of(self->subglyph0);
    self->max_contour_count = count_of(self->contour0);
    self->max_zone_count = count_of(self->zone0);
    self->max_pole_count = count_of(self->pole0);
    self->max_hint_count = count_of(self->hint0);
    self->max_hint_range_count = count_of(self->hint_range0);
    self->max_hint_applying_count = count_of(self->hint_applying0);
    self->max_stem_snap_count[0] = count_of(self->stem_snap0[0]);
    self->max_stem_snap_count[1] = count_of(self->stem_snap0[1]);
    self->max_stem_snap_vote_count = count_of(self->stem_snap_vote0);

    self->pole = self->pole0;
    self->hint = self->hint0;
    self->zone = self->zone0;
    self->contour = self->contour0;
    self->subglyph = self->subglyph0;
    self->hint_range = self->hint_range0;
    self->hint_applying = self->hint_applying0;
    self->stem_snap[0] = self->stem_snap0[0];
    self->stem_snap[1] = self->stem_snap0[1];
    self->stem_snap_vote = self->stem_snap_vote0;

    self->FontType = 1;
    self->ForceBold = false;
    self->base_font_scale = 0;
    self->resolution = 0;
    self->heigt_transform_coef = self->width_transform_coef = 0;
    self->heigt_transform_coef_rat = self->width_transform_coef_rat = 0;
    self->heigt_transform_coef_inv = self->width_transform_coef_inv = 0;
    self->cx = self->cy = 0;
    self->contour[0] = 0;
    self->subglyph[0] = 0;
    self->keep_stem_width = false;
    self->charpath_flag = false;
    self->grid_fit_x = self->grid_fit_y = true;
    self->output_path = output_path;
    self->memory = (output_path == 0 ? 0 : output_path->memory);
    self->disable_hinting = (self->memory == NULL);
    self->pass_through = self->disable_hinting;
    self->autohinting = false;
    self->fix_contour_sign = false;

    self->stem_snap[0][0] = self->stem_snap[1][0] = 100;
}
