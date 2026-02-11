print_value(union jackctl_parameter_value value, jackctl_param_type_t type)
{
    switch (type) {

        case JackParamInt:
            printf("parameter value = %d\n", value.i);
            break;

         case JackParamUInt:
            printf("parameter value = %u\n", value.ui);
            break;

         case JackParamChar:
            printf("parameter value = %c\n", value.c);
            break;

         case JackParamString:
            printf("parameter value = %s\n", value.str);
            break;

         case JackParamBool:
            printf("parameter value = %d\n", value.b);
            break;
     }
}
