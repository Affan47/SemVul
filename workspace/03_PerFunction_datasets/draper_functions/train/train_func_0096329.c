slurmdb_qos_flags_str(uint32_t flags)
{
	char *qos_flags = NULL;

	if (flags & QOS_FLAG_NOTSET)
		return xstrdup("NotSet");

	if (flags & QOS_FLAG_ADD)
		xstrcat(qos_flags, "Add,");
	if (flags & QOS_FLAG_REMOVE)
		xstrcat(qos_flags, "Remove,");
	if (flags & QOS_FLAG_DENY_LIMIT)
		xstrcat(qos_flags, "DenyOnLimit,");
	if (flags & QOS_FLAG_ENFORCE_USAGE_THRES)
		xstrcat(qos_flags, "EnforceUsageThreshold,");
	if (flags & QOS_FLAG_NO_RESERVE)
		xstrcat(qos_flags, "NoReserve,");
	if (flags & QOS_FLAG_PART_MAX_NODE)
		xstrcat(qos_flags, "PartitionMaxNodes,");
	if (flags & QOS_FLAG_PART_MIN_NODE)
		xstrcat(qos_flags, "PartitionMinNodes,");
	if (flags & QOS_FLAG_PART_TIME_LIMIT)
		xstrcat(qos_flags, "PartitionTimeLimit,");
	if (flags & QOS_FLAG_REQ_RESV)
		xstrcat(qos_flags, "RequiresReservation,");

	if (qos_flags)
		qos_flags[strlen(qos_flags)-1] = '\0';

	return qos_flags;
}
