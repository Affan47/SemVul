pygoocanvas_add_constants(PyObject *module, const gchar *strip_prefix)
{
#ifdef VERSION
    PyModule_AddStringConstant(module, "__version__", VERSION);
#endif
  pyg_enum_add(module, "AnimateType", strip_prefix, GOO_TYPE_CANVAS_ANIMATE_TYPE);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_MOVE_TO", strip_prefix), GOO_CANVAS_PATH_MOVE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_CLOSE_PATH", strip_prefix), GOO_CANVAS_PATH_CLOSE_PATH);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_LINE_TO", strip_prefix), GOO_CANVAS_PATH_LINE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_HORIZONTAL_LINE_TO", strip_prefix), GOO_CANVAS_PATH_HORIZONTAL_LINE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_VERTICAL_LINE_TO", strip_prefix), GOO_CANVAS_PATH_VERTICAL_LINE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_CURVE_TO", strip_prefix), GOO_CANVAS_PATH_CURVE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_SMOOTH_CURVE_TO", strip_prefix), GOO_CANVAS_PATH_SMOOTH_CURVE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_QUADRATIC_CURVE_TO", strip_prefix), GOO_CANVAS_PATH_QUADRATIC_CURVE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_SMOOTH_QUADRATIC_CURVE_TO", strip_prefix), GOO_CANVAS_PATH_SMOOTH_QUADRATIC_CURVE_TO);
    PyModule_AddIntConstant(module, (char *) pyg_constant_strip_prefix("GOO_CANVAS_PATH_ELLIPTICAL_ARC", strip_prefix), GOO_CANVAS_PATH_ELLIPTICAL_ARC);
  pyg_flags_add(module, "PointerEvents", strip_prefix, GOO_TYPE_CANVAS_POINTER_EVENTS);
  pyg_enum_add(module, "ItemVisibility", strip_prefix, GOO_TYPE_CANVAS_ITEM_VISIBILITY);

  if (PyErr_Occurred())
    PyErr_Print();
}
