ib_cm_insert_listen(struct ib_device *device,
				     ib_cm_handler cm_handler,
				     __be64 service_id)
{
	struct cm_id_private *cm_id_priv;
	struct ib_cm_id *cm_id;
	unsigned long flags;
	int err = 0;


	cm_id = ib_create_cm_id(device, cm_handler, NULL);
	if (IS_ERR(cm_id))
		return cm_id;

	spin_lock_irqsave(&cm.lock, flags);

	if (service_id == IB_CM_ASSIGN_SERVICE_ID)
		goto new_id;


	cm_id_priv = cm_find_listen(device, service_id);
	if (cm_id_priv) {
		if (cm_id->cm_handler != cm_handler || cm_id->context) {


			spin_unlock_irqrestore(&cm.lock, flags);
			return ERR_PTR(-EINVAL);
		}
		atomic_inc(&cm_id_priv->refcount);
		++cm_id_priv->listen_sharecount;
		spin_unlock_irqrestore(&cm.lock, flags);

		ib_destroy_cm_id(cm_id);
		cm_id = &cm_id_priv->id;
		return cm_id;
	}

new_id:

	err = __ib_cm_listen(cm_id, service_id, 0);

	spin_unlock_irqrestore(&cm.lock, flags);

	if (err) {
		ib_destroy_cm_id(cm_id);
		return ERR_PTR(err);
	}
	return cm_id;
}
