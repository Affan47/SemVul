initCalendarService(UErrorCode &status)
{
#ifdef U_DEBUG_CALSVC
        fprintf(stderr, "Spinning up Calendar Service\n");
#endif
    ucln_i18n_registerCleanup(UCLN_I18N_CALENDAR, calendar_cleanup);
    gService = new CalendarService();
    if (gService == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
        return;
        }
#ifdef U_DEBUG_CALSVC
        fprintf(stderr, "Registering classes..\n");
#endif


    gService->registerFactory(new BasicCalendarFactory(),status);

#ifdef U_DEBUG_CALSVC
        fprintf(stderr, "Done..\n");
#endif

        if(U_FAILURE(status)) {
#ifdef U_DEBUG_CALSVC
            fprintf(stderr, "err (%s) registering classes, deleting service.....\n", u_errorName(status));
#endif
        delete gService;
        gService = NULL;
    }
        }
