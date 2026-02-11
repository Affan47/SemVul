DefaultEnableRegion(SearchRegion * region, SearchInfo * info)
{
	mem_write_handler	handler = region->writeHandler->handler;
	UINT32				handlerAddress = (UINT32)handler;

	switch(info->searchSpeed)
	{
		case kSearchSpeed_Fast:

#if HAS_SH2
			if(Machine->drv->cpu[0].cpu_type == CPU_SH2)
			{
				if(	(info->targetType == kRegionType_CPU) &&
					(info->targetIdx == 0) &&
					(region->address == 0x06000000))
					return 1;

				return 0;
			}
#endif

			if(	(handler == MWA_RAM) &&
				(!region->writeHandler->base))
				return 1;

#ifndef MESS
#ifndef TINY_COMPILE
#ifndef CPSMAME

			{
				extern struct GameDriver	driver_neogeo;


				if(	(Machine->gamedrv->clone_of == &driver_neogeo) &&
					(info->targetType == kRegionType_CPU) &&
					(info->targetIdx == 0) &&
					(handler == MWA_BANK1))
					return 1;
			}

#endif
#endif
#endif

#if HAS_TMS34010


			if(	(Machine->drv->cpu[1].cpu_type == CPU_TMS34010) &&
				(info->targetType == kRegionType_CPU) &&
				(info->targetIdx == 1) &&
				(handler == MWA_BANK1))
				return 1;


			if(	(Machine->drv->cpu[0].cpu_type == CPU_TMS34010) &&
				(info->targetType == kRegionType_CPU) &&
				(info->targetIdx == 0) &&
				(handler == MWA_BANK2))
				return 1;

#endif

			return 0;

		case kSearchSpeed_Medium:
			if(	(handlerAddress >= ((UINT32)MWA_BANK1)) &&
				(handlerAddress <= ((UINT32)MWA_BANK24)))
				return 1;

			if(handler == MWA_RAM)
				return 1;

			return 0;

		case kSearchSpeed_Slow:
			if(	(handler == MWA_NOP) ||
				(handler == MWA_ROM))
				return 0;

			if(	(handlerAddress > STATIC_COUNT) &&
				(!region->writeHandler->base))
				return 0;

			return 1;

		case kSearchSpeed_VerySlow:
			if(	(handler == MWA_NOP) ||
				(handler == MWA_ROM))
				return 0;

			return 1;
	}

	return 0;
}
