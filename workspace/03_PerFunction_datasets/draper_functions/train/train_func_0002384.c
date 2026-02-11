lgl_template_frame_cd_new (const gchar         *id,
                           gdouble              r1,
                           gdouble              r2,
                           gdouble              w,
                           gdouble              h,
                           gdouble              waste)
{
        lglTemplateFrame *frame;

        frame = g_new0 (lglTemplateFrame, 1);

        frame->shape = LGL_TEMPLATE_FRAME_SHAPE_CD;
        frame->cd.id = g_strdup (id);

        frame->cd.r1 = r1;
        frame->cd.r2 = r2;
        frame->cd.w  = w;
        frame->cd.h  = h;
        frame->cd.waste = waste;

        return frame;
}
