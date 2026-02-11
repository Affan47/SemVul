vmw_resource_release_id(struct vmw_resource *res)
{
	struct vmw_private *dev_priv = res->dev_priv;
	struct idr *idr = &dev_priv->res_idr[res->func->res_type];

	write_lock(&dev_priv->resource_lock);
	if (res->id != -1)
		idr_remove(idr, res->id);
	res->id = -1;
	write_unlock(&dev_priv->resource_lock);
}
