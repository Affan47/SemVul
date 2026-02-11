init(bool register_resources_only)
{
	ref_count++;
	if (ref_count != 1) return;

	if (register_resources_only) return;

	CL_ComponentType::component_types["component"] = new CL_ComponentType_Component;
	CL_ComponentType::component_types["button"] = new CL_ComponentType_Button;
	CL_ComponentType::component_types["checkbox"] = new CL_ComponentType_CheckBox;
	CL_ComponentType::component_types["filedialog"] = new CL_ComponentType_FileDialog;
	CL_ComponentType::component_types["frame"] = new CL_ComponentType_Frame;
	CL_ComponentType::component_types["image"] = new CL_ComponentType_Image;
	CL_ComponentType::component_types["inputbox"] = new CL_ComponentType_InputBox;
	CL_ComponentType::component_types["label"] = new CL_ComponentType_Label;
	CL_ComponentType::component_types["listbox"] = new CL_ComponentType_ListBox;
	CL_ComponentType::component_types["progressbar"] = new CL_ComponentType_ProgressBar;
	CL_ComponentType::component_types["radiobutton"] = new CL_ComponentType_RadioButton;
	CL_ComponentType::component_types["scrollbar"] = new CL_ComponentType_ScrollBar;
	CL_ComponentType::component_types["window"] = new CL_ComponentType_Window;
	CL_ComponentType::component_types["treeview"] = new CL_ComponentType_TreeView;
}
