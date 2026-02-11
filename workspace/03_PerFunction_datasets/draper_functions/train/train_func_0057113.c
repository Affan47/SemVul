RegpOpenOrCreateKey(
	IN HKEY hParentKey,
	IN PCWSTR KeyName,
	IN BOOL AllowCreation,
	OUT PHKEY Key)
{
	PWSTR LocalKeyName;
	PWSTR End;
	UNICODE_STRING KeyString;
	NTSTATUS Status;
	MEMKEY ParentKey;
	MEMKEY CurrentKey;
	PLIST_ENTRY Ptr;
	PCM_KEY_NODE SubKeyCell;
	HCELL_INDEX BlockOffset;

	DPRINT("RegpCreateOpenKey('%S')\n", KeyName);

	if (*KeyName == L'\\')
	{
		KeyName++;
		ParentKey = RootKey;
	}
	else if (hParentKey == NULL)
	{
		ParentKey = RootKey;
	}
	else
	{
		ParentKey = HKEY_TO_MEMKEY(RootKey);
	}

	LocalKeyName = (PWSTR)KeyName;
	for (;;)
	{
		End = (PWSTR)strchrW(LocalKeyName, '\\');
		if (End)
		{
			KeyString.Buffer = LocalKeyName;
			KeyString.Length = KeyString.MaximumLength =
				(USHORT)((ULONG_PTR)End - (ULONG_PTR)LocalKeyName);
		}
		else
			RtlInitUnicodeString(&KeyString, LocalKeyName);


		if (!strncmpW(LocalKeyName, L"CurrentControlSet", 17) &&
		    ParentKey->NameSize == 12 &&
		    !memcmp(ParentKey->Name, L"SYSTEM", 12))
			RtlInitUnicodeString(&KeyString, L"ControlSet001");


		Ptr = ParentKey->SubKeyList.Flink;
		while (Ptr != &ParentKey->SubKeyList)
		{
			CurrentKey = CONTAINING_RECORD(Ptr, KEY, KeyList);
			if (CurrentKey->NameSize == KeyString.Length
			 && memcmp(CurrentKey->Name, KeyString.Buffer, KeyString.Length) == 0)
			{
				goto nextsubkey;
			}

			Ptr = Ptr->Flink;
		}

		Status = CmiScanForSubKey(
			ParentKey->RegistryHive,
			ParentKey->KeyCell,
			&KeyString,
			OBJ_CASE_INSENSITIVE,
			&SubKeyCell,
			&BlockOffset);
		if (AllowCreation && Status == STATUS_OBJECT_NAME_NOT_FOUND)
		{
			Status = CmiAddSubKey(
				ParentKey->RegistryHive,
				ParentKey->KeyCell,
				ParentKey->KeyCellOffset,
				&KeyString,
				0,
				&SubKeyCell,
				&BlockOffset);
		}
		if (!NT_SUCCESS(Status))
			return ERROR_UNSUCCESSFUL;


		CurrentKey = CreateInMemoryStructure(
			ParentKey->RegistryHive,
			BlockOffset,
			&KeyString);
		if (!CurrentKey)
			return ERROR_OUTOFMEMORY;


		InsertTailList(&ParentKey->SubKeyList, &CurrentKey->KeyList);
		ParentKey->SubKeyCount++;

nextsubkey:
		ParentKey = CurrentKey;
		if (End)
			LocalKeyName = End + 1;
		else
			break;
	}

	*Key = MEMKEY_TO_HKEY(ParentKey);

	return ERROR_SUCCESS;
}
