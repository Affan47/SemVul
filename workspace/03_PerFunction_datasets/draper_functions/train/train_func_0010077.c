ata_cmd_write_callback(struct pcmcia_disk_data *d)
{

   disk_write_sector(d,d->sect_pos,d->data_buffer);
   d->ata_status = ATA_STATUS_RDY|ATA_STATUS_DSC|ATA_STATUS_DRQ;
   d->sect_pos++;

   d->sect_remaining--;

   if (!d->sect_remaining) {
      d->ata_status = ATA_STATUS_RDY|ATA_STATUS_DSC;
   }
}
