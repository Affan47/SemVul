json_value_string(json_value * value) {
   static char buf[512];

   switch(value->type) {
      case json_string:
         return value->u.string.ptr;

      case json_boolean:
         return value->u.boolean ? "true" : "false";

      case json_integer:
         snprintf(buf, sizeof(buf), "%li", value->u.integer);
         return buf;

      case json_double:
         snprintf(buf, sizeof(buf), "%f", value->u.dbl);
         return buf;

      default:
         return NULL;
   }
}
