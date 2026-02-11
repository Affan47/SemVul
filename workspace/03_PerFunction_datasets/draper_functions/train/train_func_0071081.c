serio_cleanup(struct serio *serio)
{
	mutex_lock(&serio->drv_mutex);
	if (serio->drv && serio->drv->cleanup)
		serio->drv->cleanup(serio);
	mutex_unlock(&serio->drv_mutex);
}
