DropHeldItemToInventory(void)
{
	point CurPos;
	int FreeInvIndex;
	int i;
	FreeInvIndex = GetFreeInventoryIndex();


	if (item_held_in_hand == NULL) {
		DebugPrintf(0, "\nvoid DropHeldItemToInventory ( void ) : No item in inventory seems to be currently held in hand...");
		return;
	}


	CurPos.x = GetMousePos_x() - (16 * (ItemMap[item_held_in_hand->type].inv_size.x - 1));
	CurPos.y = GetMousePos_y() - (16 * (ItemMap[item_held_in_hand->type].inv_size.y - 1));

	if (ItemCanBeDroppedInInv(item_held_in_hand->type, GetInventorySquare_x(CurPos.x), GetInventorySquare_y(CurPos.y))) {
		CopyItem(item_held_in_hand, &(Me.Inventory[FreeInvIndex]));
		play_item_sound(item_held_in_hand->type, &Me.pos);
		Me.Inventory[FreeInvIndex].inventory_position.x = GetInventorySquare_x(CurPos.x);
		Me.Inventory[FreeInvIndex].inventory_position.y = GetInventorySquare_y(CurPos.y);


		DeleteItem(item_held_in_hand);
		item_held_in_hand = NULL;
		return;
	} else {


		for (i = 0; i < MAX_ITEMS_IN_INVENTORY - 1; i++) {


			if (&(Me.Inventory[i]) == item_held_in_hand)
				continue;


			CopyItem(&(Me.Inventory[i]), &(Me.Inventory[MAX_ITEMS_IN_INVENTORY - 1]));
			Me.Inventory[i].type = (-1);

			if (ItemCanBeDroppedInInv(item_held_in_hand->type, GetInventorySquare_x(CurPos.x), GetInventorySquare_y(CurPos.y))) {


				CopyItem(item_held_in_hand, &(Me.Inventory[FreeInvIndex]));
				play_item_sound(item_held_in_hand->type, &Me.pos);
				Me.Inventory[FreeInvIndex].inventory_position.x = GetInventorySquare_x(CurPos.x);
				Me.Inventory[FreeInvIndex].inventory_position.y = GetInventorySquare_y(CurPos.y);
				DeleteItem(item_held_in_hand);


				MakeHeldFloorItemOutOf(&(Me.Inventory[MAX_ITEMS_IN_INVENTORY - 1]));

				return;
			}


			CopyItem(&(Me.Inventory[MAX_ITEMS_IN_INVENTORY - 1]), &(Me.Inventory[i]));

		}
	}
}
