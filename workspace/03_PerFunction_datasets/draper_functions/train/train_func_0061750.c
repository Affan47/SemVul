emit_interpolation_setup_gen4()
{
   this->current_annotation = "compute pixel centers";
   this->pixel_x = fs_reg(this, glsl_type::uint_type);
   this->pixel_y = fs_reg(this, glsl_type::uint_type);
   this->pixel_x.type = BRW_REGISTER_TYPE_UW;
   this->pixel_y.type = BRW_REGISTER_TYPE_UW;

   emit(FS_OPCODE_PIXEL_X, this->pixel_x);
   emit(FS_OPCODE_PIXEL_Y, this->pixel_y);

   this->current_annotation = "compute pixel deltas from v0";
   if (brw->has_pln) {
      this->delta_x[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC] =
         fs_reg(this, glsl_type::vec2_type);
      this->delta_y[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC] =
         this->delta_x[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC];
      this->delta_y[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC].reg_offset++;
   } else {
      this->delta_x[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC] =
         fs_reg(this, glsl_type::float_type);
      this->delta_y[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC] =
         fs_reg(this, glsl_type::float_type);
   }
   emit(ADD(this->delta_x[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC],
            this->pixel_x, fs_reg(negate(brw_vec1_grf(1, 0)))));
   emit(ADD(this->delta_y[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC],
            this->pixel_y, fs_reg(negate(brw_vec1_grf(1, 1)))));

   this->current_annotation = "compute pos.w and 1/pos.w";


   this->wpos_w = fs_reg(this, glsl_type::float_type);
   emit(FS_OPCODE_LINTERP, wpos_w,
        this->delta_x[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC],
        this->delta_y[BRW_WM_PERSPECTIVE_PIXEL_BARYCENTRIC],
	interp_reg(VARYING_SLOT_POS, 3));

   this->pixel_w = fs_reg(this, glsl_type::float_type);
   emit_math(SHADER_OPCODE_RCP, this->pixel_w, wpos_w);
   this->current_annotation = NULL;
}
