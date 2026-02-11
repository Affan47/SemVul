ready() {
	cpX = ((double)width-1.0)/2.0;
	cpY = ((double)height-1.0)/2.0;


    std::cout << "in raycreator::ready sizeV " << sizeV << " cam " << cam << " planeC " << planeC << " planeN " << planeN << std::endl;

    return cam && planeC && planeN;
}
