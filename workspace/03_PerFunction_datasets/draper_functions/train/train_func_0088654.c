window_deactivated_idle (GSManager *manager)
{
        g_return_val_if_fail (manager != NULL, FALSE);
        g_return_val_if_fail (GS_IS_MANAGER (manager), FALSE);


        g_signal_emit (manager, signals [DEACTIVATED], 0);

        return FALSE;
}
