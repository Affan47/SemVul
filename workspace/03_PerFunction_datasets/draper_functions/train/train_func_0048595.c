undo (unsigned int n)
{
	if (n == 0) {
		return;
	}

	{
		UndoRedoSignaller exception_safe_signaller (*this);

		while (n--) {
			if (UndoList.size() == 0) {
				return;
			}
			UndoTransaction* ut = UndoList.back ();
			UndoList.pop_back ();
			ut->undo ();
			RedoList.push_back (ut);
		}
	}

	Changed ();
}
