esp_map_dma(struct esp *esp, struct scsi_cmnd *cmd)
{
	struct esp_cmd_priv *spriv = ESP_CMD_PRIV(cmd);
	struct scatterlist *sg = scsi_sglist(cmd);
	int dir = cmd->sc_data_direction;
	int total, i;

	if (dir == DMA_NONE)
		return;

	spriv->u.num_sg = esp->ops->map_sg(esp, sg, scsi_sg_count(cmd), dir);
	spriv->cur_residue = sg_dma_len(sg);
	spriv->cur_sg = sg;

	total = 0;
	for (i = 0; i < spriv->u.num_sg; i++)
		total += sg_dma_len(&sg[i]);
	spriv->tot_residue = total;
}
