draw_fillet_triangle_plain
                          (gleDouble va[3],
                           gleDouble vb[3],
                           gleDouble vc[3],
                           int face,
                           float front_color[3],
                           float back_color[3])
{

   if (front_color != NULL) C3F (front_color);
   BGNTMESH (-5, 0.0);
   if (face) {
      V3F (va, INVALID_BUG_NEEDS_FIXING, FILLET);
      V3F (vb, INVALID_BUG_NEEDS_FIXING, FILLET);
   } else {
      V3F (vb, INVALID_BUG_NEEDS_FIXING, FILLET);
      V3F (va, INVALID_BUG_NEEDS_FIXING, FILLET);
   }
   V3F (vc, INVALID_BUG_NEEDS_FIXING, FILLET);
   ENDTMESH ();

}
