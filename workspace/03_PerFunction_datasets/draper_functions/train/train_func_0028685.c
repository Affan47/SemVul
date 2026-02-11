e_sys_action_possible_get(E_Sys_Action a)
{
   switch (a)
     {
      case E_SYS_EXIT:
      case E_SYS_RESTART:
      case E_SYS_EXIT_NOW:
        return 1;

      case E_SYS_LOGOUT:
        return 1;

      case E_SYS_HALT:
      case E_SYS_HALT_NOW:
        return _e_sys_can_halt;

      case E_SYS_REBOOT:
        return _e_sys_can_reboot;

      case E_SYS_SUSPEND:
        return _e_sys_can_suspend;

      case E_SYS_HIBERNATE:
        return _e_sys_can_hibernate;

      default:
        return 0;
     }
   return 0;
}
