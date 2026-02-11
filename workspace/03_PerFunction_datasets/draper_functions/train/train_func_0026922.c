add_aspect_include (JoinPointLoc *jpl, AspectInfo &aspect_info,
#endif
  AspectRef::Kind kind) {
  Unit *iu;

#ifdef ACMODEL
  if (jpl && is_pseudo(*jpl))
    return;

  ACM_Aspect &jpl_aspect = aspect_info.loc ();
#else
  if (jpl && jpl->type () == JoinPointLoc::MethodCall &&
      ((JPL_Code*)jpl)->is_pseudo ())
    return;

  JPL_Aspect &jpl_aspect = aspect_info.loc ();
#endif

  if (!jpl)

    iu = TI_Aspect::of (jpl_aspect)->ClassInfo ()->SourceInfo ()->FileInfo ()->Primary ();
  else {
    iu = TransformInfo::unit (*jpl);
  }


  IntroductionUnit *intro_unit = 0;
  while ((intro_unit = IntroductionUnit::cast (iu)) != 0)
    iu = intro_unit->target_unit ();

  _aspect_includes.insert (iu, &aspect_info, kind);
}
