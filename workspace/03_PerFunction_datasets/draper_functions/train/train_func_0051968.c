draw_scope(vpiHandle item)
{
      int depth;
      const char *name;

      vpiHandle scope = vpi_handle(vpiScope, item);
      if (!scope) return 0;

      depth = 1 + draw_scope(scope);
      name = vpi_get_str(vpiName, scope);

      push_scope(name);

      return depth;
}
