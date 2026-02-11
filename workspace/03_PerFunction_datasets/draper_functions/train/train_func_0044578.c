mgrib_drawnormal(HPoint3 *p, Point3 *n) {
  HPoint3 end, tp;
  float scale;
  Color *color;

  if (p->w <= 0.0) return;
  scale = p->w * _mgc->astk->ap.nscale;
  end.x = p->x + scale*n->x;
  end.y = p->y + scale*n->y;
  end.z = p->z + scale*n->z;
  end.w = p->w;

  color = &_mgc->astk->mat.normalcolor;
  mrti(mr_attributebegin, mr_surface, mr_constant,
       mr_color, mr_parray, 3, color,
       mr_opacity, mr_array, 3, 1., 1., 1., mr_NULL);
  mgrib_drawline(&tp,&end);
  mrti(mr_attributeend, mr_NULL);

}
