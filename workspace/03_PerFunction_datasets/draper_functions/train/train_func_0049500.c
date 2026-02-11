e_sys_action_raw_do(E_Sys_Action a, char *param)
{
   int ret = 0;

   if (_e_sys_action_current != E_SYS_NONE)
     {
        _e_sys_current_action();
        return 0;
     }
   switch (a)
     {
      case E_SYS_EXIT:
      case E_SYS_RESTART:
      case E_SYS_EXIT_NOW:
      case E_SYS_LOGOUT:
      case E_SYS_SUSPEND:
      case E_SYS_HIBERNATE:
      case E_SYS_HALT_NOW:
        ret = _e_sys_action_do(a, param, EINA_TRUE);
        break;

      case E_SYS_HALT:
      case E_SYS_REBOOT:
        if (!e_util_immortal_check()) _e_sys_logout_begin(a, EINA_TRUE);
        return 1;
        break;

      default:
        break;
     }

   if (ret) _e_sys_action_current = a;
   else _e_sys_action_current = E_SYS_NONE;

   return ret;
}
