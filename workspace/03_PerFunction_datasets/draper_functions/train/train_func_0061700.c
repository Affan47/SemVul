store_will_buy(int store_num, const object_type *o_ptr)
{

	if (store_num == STORE_HOME) return (TRUE);


	switch (store_num)
	{

		case STORE_GENERAL:
		{
			size_t i;
			bool accept = FALSE;


			if (o_ptr->tval == TV_LIGHT || o_ptr->tval == TV_FOOD)
			    accept = TRUE;


			for (i = 0; !accept && i < N_ELEMENTS(staples); i++)
			{
				if (staples[i].tval == o_ptr->tval &&
				    staples[i].sval == o_ptr->sval)
					accept = TRUE;
			}

			if (!accept) return FALSE;
			break;
		}


		case STORE_ARMOR:
		{

			switch (o_ptr->tval)
			{
				case TV_BOOTS:
				case TV_GLOVES:
				case TV_CROWN:
				case TV_HELM:
				case TV_SHIELD:
				case TV_CLOAK:
				case TV_SOFT_ARMOR:
				case TV_HARD_ARMOR:
				case TV_DRAG_ARMOR:
					break;

				default:
					return (FALSE);
			}
			break;
		}


		case STORE_WEAPON:
		{

			switch (o_ptr->tval)
			{
				case TV_SHOT:
				case TV_BOLT:
				case TV_ARROW:
				case TV_BOW:
				case TV_DIGGING:
				case TV_HAFTED:
				case TV_POLEARM:
				case TV_SWORD:
					break;

				default:
					return (FALSE);
			}
			break;
		}


		case STORE_TEMPLE:
		{

			switch (o_ptr->tval)
			{
				case TV_PRAYER_BOOK:
				case TV_SCROLL:
				case TV_POTION:
				case TV_HAFTED:
					break;

				case TV_POLEARM:
				case TV_SWORD:
				{

					if (object_is_known_blessed(o_ptr)) break;
				}

				default:
					return (FALSE);
			}
			break;
		}


		case STORE_ALCHEMY:
		{

			switch (o_ptr->tval)
			{
				case TV_SCROLL:
				case TV_POTION:
					break;

				default:
					return (FALSE);
			}
			break;
		}


		case STORE_MAGIC:
		{

			switch (o_ptr->tval)
			{
				case TV_MAGIC_BOOK:
				case TV_AMULET:
				case TV_RING:
				case TV_STAFF:
				case TV_WAND:
				case TV_ROD:
				case TV_SCROLL:
				case TV_POTION:
					break;

				default:
					return (FALSE);
			}
			break;
		}
	}


	if (object_value(o_ptr, 1, FALSE) <= 0) return (FALSE);


	return (TRUE);
}
