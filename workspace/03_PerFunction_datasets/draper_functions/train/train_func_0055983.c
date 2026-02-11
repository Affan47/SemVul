add_action (const std::string icon,
				     const std::string label,
				     boost::function0<void> callback)
{
  if (active)
    builder.add_action (icon, label, callback);
}
