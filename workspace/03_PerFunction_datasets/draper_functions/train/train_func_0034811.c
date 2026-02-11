cpufreq_selector_sysfs_finalize (GObject *object)
{
        CPUFreqSelectorSysfs *selector = CPUFREQ_SELECTOR_SYSFS (object);

        if (selector->priv->available_freqs) {
                g_list_foreach (selector->priv->available_freqs,
                                (GFunc) g_free,
				NULL);
                g_list_free (selector->priv->available_freqs);
                selector->priv->available_freqs = NULL;
	}

        if (selector->priv->available_govs) {
                g_list_foreach (selector->priv->available_govs,
                                (GFunc) g_free,
				NULL);
                g_list_free (selector->priv->available_govs);
                selector->priv->available_govs = NULL;
	}

	G_OBJECT_CLASS (cpufreq_selector_sysfs_parent_class)->finalize (object);
}
