deviceSendDiscoverRequest(std::string deviceName, Address address, std::vector<std::string>* returnedNodes, std::vector<std::string>* returnedLeaves, std::vector<std::string>* returnedAttributes)
{
	Device* currentDevice;
	std::map<std::string, Device*>::iterator it;
	std::map<std::string, Plugin*>::iterator it2;


	it = netDevices->find(deviceName);

	if (it != netDevices->end()) {

		currentDevice = it->second;


		it2 = netPlugins->find(currentDevice->getPluginToUse());

		if (it2 != netPlugins->end() && it2->second != NULL)
			return it2->second->deviceSendDiscoverRequest(currentDevice, address, returnedNodes, returnedLeaves, returnedAttributes);
		else
			std::cout << "DeviceManager::deviceSendDiscoverRequest : no plugin for the device named " << deviceName << std::endl;
	}else
		std::cout << "DeviceManager::deviceSendDiscoverRequest : no device named " << deviceName << std::endl;

	return NO_ANSWER;
}
