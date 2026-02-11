ctxs_destroy(isc_mem_t **mctxp, isc_appctx_t **actxp,
	     isc_taskmgr_t **taskmgrp, isc_socketmgr_t **socketmgrp,
	     isc_timermgr_t **timermgrp)
{
	if (taskmgrp != NULL)
		isc_taskmgr_destroy(taskmgrp);

	if (timermgrp != NULL)
		isc_timermgr_destroy(timermgrp);

	if (socketmgrp != NULL)
		isc_socketmgr_destroy(socketmgrp);

	if (actxp != NULL)
		isc_appctx_destroy(actxp);

	if (mctxp != NULL)
		isc_mem_destroy(mctxp);
}
