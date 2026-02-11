my_cpu(RESULT * result, RESULT * arg1, RESULT * arg2)
{
    char *key;
    int delay;
    double value;
    double cpu_user, cpu_nice, cpu_system, cpu_idle, cpu_total;
    double cpu_iow, cpu_irq, cpu_sirq;

    if (parse_proc_stat() < 0) {
	SetResult(&result, R_STRING, "");
	return;
    }

    key = R2S(arg1);
    delay = R2N(arg2);

    cpu_user = hash_get_delta(&Stat, "cpu.user", NULL, delay);
    cpu_nice = hash_get_delta(&Stat, "cpu.nice", NULL, delay);
    cpu_system = hash_get_delta(&Stat, "cpu.system", NULL, delay);
    cpu_idle = hash_get_delta(&Stat, "cpu.idle", NULL, delay);


    cpu_iow = hash_get_delta(&Stat, "cpu.iow", NULL, delay);
    cpu_irq = hash_get_delta(&Stat, "cpu.irq", NULL, delay);
    cpu_sirq = hash_get_delta(&Stat, "cpu.sirq", NULL, delay);

    cpu_total = cpu_user + cpu_nice + cpu_system + cpu_idle + cpu_iow + cpu_irq + cpu_sirq;

    if (strcasecmp(key, "user") == 0)
	value = cpu_user;
    else if (strcasecmp(key, "nice") == 0)
	value = cpu_nice;
    else if (strcasecmp(key, "system") == 0)
	value = cpu_system;
    else if (strcasecmp(key, "idle") == 0)
	value = cpu_idle;
    else if (strcasecmp(key, "iowait") == 0)
	value = cpu_iow;
    else if (strcasecmp(key, "irq") == 0)
	value = cpu_irq;
    else if (strcasecmp(key, "softirq") == 0)
	value = cpu_sirq;
    else if (strcasecmp(key, "busy") == 0)
	value = cpu_total - cpu_idle;

    if (cpu_total > 0.0)
	value = 100 * value / cpu_total;
    else
	value = 0.0;

    SetResult(&result, R_NUMBER, &value);
}
