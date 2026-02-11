ata_link_online(struct ata_link *link)
{
	struct ata_link *slave = link->ap->slave_link;

	WARN_ON(link == slave);

	return ata_phys_link_online(link) ||
		(slave && ata_phys_link_online(slave));
}
